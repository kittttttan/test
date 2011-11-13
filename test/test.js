if (typeof load != 'undefined') {
  load('../lib.js');
  load('../sprintf.js');
  load('../array.js');
  load('../string.js');
  load('../strconv.js');
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

function mainTest() {
  var d = +new Date;

  sprintfTest();
  rangeTest();
  genRandomStringTest();
  strConvTest();

  stdout((new Date - d) +'ms');
}

mainTest();
