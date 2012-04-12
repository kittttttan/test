if (typeof load != 'undefined') {
  load('../lib.js');
  load('../sprintf.js');
  load('../array.js');
  load('../string.js');
  load('../strconv.js');
  load('../date.js');
}

function sprintfTest() {
  stdout('Test sprintf ...');
  stdout(
    sprintf('%%02d, 7 -> %02d\n%%#x, 100 -> %#x\n%%+.2f, 6.789 -> %+.2f\n%%.3e, 12.3 -> %.3e\n',
        7, 100, 6.789, 12.3)
  );
}

function rangeTest() {
  stdout('Test range ...');
  stdout('range(7) = '+ range(7));
  stdout('range(3, 0, -0.5) = '+ range(3, 0, -0.5));
}

function genRandomStringTest() {
  stdout('Test genRandomString ...');
  stdout('genRandomString(10) = '+ genRandomString(10));
  stdout('genRandomString(7, 48) = '+ genRandomString(7, 48));
}

function strConvTest() {
  stdout('Test strConv ...');
  stdout('proper("sample test") = '+ proper('sample text'));
  stdout('toZenkaku("sample test") = '+ toZenkaku('sample text'));
}

function dateFormatTest() {
  stdout('Test dateFormat ...');
  var d = new Date();
  stdout(dateFormat('yyyy-MM-dd E', d));
  stdout(dateFormat('M/d a hh:mm:ss.SZ', d));
  stdout(dateFormat('MMM, yy', d));
}

function nativeDateTest() {
  stdout('Test Date#method ...');
  var d = new Date();
  stdout(d.toString());
  stdout(d.toUTCString());
  stdout(d.toLocaleString());
  stdout(d.toJSON && d.toJSON());
  stdout(d.getTime());
  stdout(d.getFullYear());
  stdout(d.getMonth());
  stdout(d.getDate());
  stdout(d.getDay());
  stdout(d.getHours());
  stdout(d.getMinutes());
  stdout(d.getSeconds());
  stdout(d.getMilliseconds());
  stdout(d.getTimezoneOffset());
}

function mainTest() {
  var d = Date.now();

  sprintfTest();
  rangeTest();
  genRandomStringTest();
  strConvTest();
  dateFormatTest();

  stdout((Date.now() - d) +'ms');
}

mainTest();
