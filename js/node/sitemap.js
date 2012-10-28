var fs = require('fs'),
    util = require('util'),
    
    date = require('../date'),
    string = require('../string'),

    domain = 'http://kittttttan.web.fc2.com',
    out = '<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n'+
          '<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n';

function ls(path) {
  var files = fs.readdirSync(path),
      l = files.length,
      prefix = (path.length > 2 ? path + '/' : './'),
      i, stat, fname, mtime;
  for (i = 0; i < l; ++i) {
    fname = prefix + files[i];
    stat = fs.statSync(fname);
    if (stat.isFile()) {
      if (string.endsWith(files[i], '.htm') ||
          string.endsWith(files[i], '.html')) {
        mtime = date.dateFormat('yyyy-MM-dd', stat.mtime);
        out += '<url><loc>'+ domain + fname.substring(1) +
              '</loc><lastmod>'+ mtime + '</lastmod></url>\n';
      }
    } else if (stat.isDirectory()) {
      ls(fname);
    }
  }
}

try {
  ls('./');
  out += '</urlset>';
  
  fs.writeFile('./sitemap.xml', out, function(err) {
    if (err) throw err;
  });
} catch (e) {
  console.log(e);
}