#!C:\Python33\python.exe
# -*- coding: utf-8 -*-

import cgi
import cgitb; cgitb.enable()
import os, sys
try: # Windows needs stdio set for binary mode.
    import msvcrt
    msvcrt.setmode (0, os.O_BINARY) # stdin  = 0
    msvcrt.setmode (1, os.O_BINARY) # stdout = 1
except ImportError:
    pass

def main():
    UPLOAD_DIR = './upload'
    HTML_TEMPLATE = """Content-Type: text/html

<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>upload</title>
</head>
<body>
<form action="upload.py" method="post" enctype="multipart/form-data">
  <input name="file" type="file"><br>
  <input name="submit" type="submit">
</form>
<p>%(RESULT)s</p>
</body>
</html>
"""

    result = ''
    form = cgi.FieldStorage()
    if 'file' in form:
        item = form['file']
        if item.file:
            try:
                with open(os.path.join(UPLOAD_DIR, item.filename), 'wb') as fout:
                    while 1:
                        chunk = item.file.read(100000)
                        if not chunk: break
                        fout.write(chunk)
                result = 'upload success'
            except:
                result = 'error'

    print(HTML_TEMPLATE % {'RESULT':result})

if __name__ == '__main__':
    main()