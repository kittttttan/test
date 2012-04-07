var http = require('http'),
    fs = require('fs'),
    root = __dirname,
    MIME = {
      '.htm': 'text/html',
      '.html': 'text/html',
      '.txt': 'text/plain',
      '.ico': 'image/vnd.microsoft.icon',
      '.bmp': 'image/bmp',
      '.gif': 'image/gif',
      '.jpg': 'image/jpeg',
      '.png': 'image/png',
      '.css': 'text/css',
      '.js': 'text/javascript',
      '.xml': 'application/xml',
      '.zip': 'application/zip'
    };

http.createServer(function(req, res) {
  console.log('start');
  if (req.method == 'POST') {
      res.writeHead(200, {'Content-Type': 'text/plain'});
      res.end('Hello World\n');
    return;
  } else {
    var reqUrl = require('url').parse(req.url), body;
    console.log(reqUrl);
    if (reqUrl === '/') {
      reqUrl = '/index.html';
    }

    var ext, dot = reqUrl.lastIndexOf('.');
    if (dot < 0) {
      ext = '.html';
      reqUrl += ext;
    } else {
      ext = reqUrl.substring(dot);
    }
    if (ext in MIME) {
      try {
        body = fs.readFileSync(root + reqUrl);
        res.writeHead(200, {'content-type': MIME[ext], 'content-length': body.length});
        res.write(body);
        res.end();
      } catch(e) {
        console.log(e.message);
        res.writeHead(404, {'content-type': 'text/plain'});
        res.end('404 not found\n');
      }
    } else {
      res.writeHead(403, {'content-type': 'text/plain'});
      res.end('403 forbidden\n');        
    }
  }
  console.log('end');
}).listen(1337, '127.0.0.1');
console.log('Server running at http://127.0.0.1:1337/');
