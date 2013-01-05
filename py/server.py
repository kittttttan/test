'''Tiny CGI Server for python3

example:
    python server.py localhost 8000
  
    and access
    http://localhost:8000/
'''

from http.server import HTTPServer, CGIHTTPRequestHandler
from sys import argv

class CustomCGIHandler(CGIHTTPRequestHandler):
    # override if you need
    cgi_directories = ['/cgi-bin', '/htbin']

def run_server(address, port):
    try:
        httpd = HTTPServer((address, port), CustomCGIHandler)
        print('Serving %s:%s' % (address, port))
        httpd.serve_forever()
    except KeyboardInterrupt:
        print('Server killed.')
    except:
        print('Unexpected error %s:%s' % (address, port))

def main():
    # default
    address = 'localhost'
    port = 80

    # option
    if len(argv) > 1:
        if argv[1] in ('-h','--help'):
            print('  python server.py [address [port]]')
            return
        address = argv[1]
    if len(argv) > 2:
        port = int(argv[2])

    run_server(address, port)

if __name__ == "__main__":
    main()
