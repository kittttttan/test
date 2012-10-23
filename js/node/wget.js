var http = require('http'),
    https = require('https'),
    url = require('url'),
    fs = require('fs');

function wget(targetUrl, opt) {
  var callee = arguments.callee;
  var target = url.parse(targetUrl);
  var req = (/https/.test(target.protocol) ? https : http).request({
    host: target.hostname,
    port: target.port,
    path: target.pathname + (target.search || ''),
    method: opt.method
  });
  console.log(req.method +' '+ targetUrl);
  
  req.on('response', function(res){
    if (res.statusCode === 301 || res.statusCode === 302) {
      console.log(res.statusCode +' redirect ' + res.headers.location);
      callee(res.headers.location, opt);
    } else if (res.statusCode === 200) {
      var wstream, err = false;
      if (opt.filepath) {
        wstream = fs.createWriteStream(opt.filepath);
        wstream.on('error', function(e) {
          err = true;
          opt.callback(e);
        }).on('close', opt.callback);
      }
      res.on('data', function(chunk){
        wstream.write(chunk, 'binary');
      }).on('end', function(){
        if (wstream) {
          if (!err) { wstream.end(); }
        }
        console.log(res.statusCode +' OK');
      });
    } else {
      opt.callback(new Error('statusCode is ' + res.statusCode));
    }
  }).on('error', opt.callback);
  req.end();
}

function main() {
  var opt = {
    method: 'GET',
    filepath: 'kittttttan.html',
    callback: function(err) {
      if (err) {
        console.log(err);
        return;
      }
      console.log('done! '+ opt.filepath);
    }
  };
  
  wget('http://kittttttan.web.fc2.com/', opt);
}

main();