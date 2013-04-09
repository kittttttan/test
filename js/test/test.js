if (typeof require != 'undefined') {
  var lib = require('../lib.js');
  var assert = lib.assert;
  
  var uu = require('../uuid.js');
  var uuid = uu.uuid;
  
  var sp = require('../sprintf.js');
  var sprintf = sp.sprintf;
  
  var array = require('../array.js');
  var range = array.range;
  
  var string = require('../string.js');
  var genRandomString = string.genRandomString;
  
  var strconv = require('../strconv.js');
  var proper = strconv.proper;
  var toZenkaku = strconv.toZenkaku;
  
  var date = require('../date.js');
  var dateFormat = date.dateFormat;
}

if (typeof console == 'undefined') {
  console={
    log: function(a){
      document.writeln(a);
    }
  };
}

function uuidTest() {
  console.log('Test uuid ...');
  var u = uuid();
  console.log('version: '+ u.version());
  console.log('variant: '+ u.variant());
  var id = u.generate();
  console.log(id);
  u.fromString(id);
  console.log(u.toString());
  console.log('');
}

function sprintfTest() {
  console.log('Test sprintf ...');
  console.log(
    sprintf('%%02d, 7 -> %02d\n%%#x, 100 -> %#x\n%%+.2f, 6.789 -> %+.2f\n%%.3e, 12.3 -> %.3e\n',
        7, 100, 6.789, 12.3)
  );
}

function rangeTest() {
  console.log('Test range ...');
  console.log('range(7) = '+ range(7));
  console.log('range(3, 0, -0.5) = '+ range(3, 0, -0.5));
  console.log('');
}

function genRandomStringTest() {
  console.log('Test genRandomString ...');
  console.log('genRandomString(10) = '+ genRandomString(10));
  console.log('genRandomString(7, 48) = '+ genRandomString(7, 48));
  console.log('');
}

function strConvTest() {
  console.log('Test strConv ...');
  console.log('proper("sample test") = '+ proper('sample text'));
  console.log('toZenkaku("sample test") = '+ toZenkaku('sample text'));
  console.log('');
}

function dateFormatTest() {
  console.log('Test dateFormat ...');
  var d = new Date();
  console.log(dateFormat('yyyy-MM-dd E', d));
  console.log(dateFormat('M/d a hh:mm:ss.SZ', d));
  console.log(dateFormat('MMM, yy', d));
  console.log('');
}

function nativeDateTest() {
  console.log('Test Date#method ...');
  var d = new Date();
  console.log(d.toString());
  console.log(d.toUTCString());
  console.log(d.toLocaleString());
  console.log(d.toJSON && d.toJSON());
  console.log(d.getTime());
  console.log(d.getFullYear());
  console.log(d.getMonth());
  console.log(d.getDate());
  console.log(d.getDay());
  console.log(d.getHours());
  console.log(d.getMinutes());
  console.log(d.getSeconds());
  console.log(d.getMilliseconds());
  console.log(d.getTimezoneOffset());
  console.log('');
}

function mainTest() {
  var d = Date.now();
  
  uuidTest();
  sprintfTest();
  rangeTest();
  genRandomStringTest();
  strConvTest();
  dateFormatTest();

  console.log((Date.now() - d) +'ms');
}

mainTest();
//assert(false, 'assert test');
