/// <reference path="../date.ts"/>
import date = module('../date');

function dateFormatTest() {
  console.log('Test dateFormat ...');
  var d = new Date();
  console.log(date.format('yyyy-MM-dd E', d));
  console.log(date.format('M/d a hh:mm:ss.SZ', d));
  console.log(date.format('MMM, yy', d));
}

dateFormatTest();
