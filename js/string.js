/**
 * @param {string} s
 * @return {string}
 */
function escapeHTML(s) {
  return s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;')
      .replace(/'/g, '&apos;').replace(/"/g, '&quot;'); // '
}

/**
 * @param {string} s
 * @return {string}
 */
function escapeJS(s) {
  return s.replace(/\\/g, '\\\\').replace(/"/g, '\\"')
      .replace(/'/g, "\\'").replace(/\//g, '\\/') // '
      // .replace(/</g, '\\x3c').replace(/>/g, '\\x3e')
      ;
}

/**
 * @param {string} s
 * @return {string}
 */
function trimLeft(s) {
  return s.replace(/^\s+$/, '');
}

/**
 * @param {string} s
 * @return {string}
 */
function trimRight(s) {
  return s.replace(/\s+$/, '');
}

/**
 * @param {string} s
 * @return {string}
 */
function trim(s) {
  return s.replace(/^\s+|\s+$/, '');
}

/**
 * @param {string} s
 * @return {string}
 */
function nobr(s) {
  return s.replace(/[\r\n]+/g, '');
}

// RegExp snippets
var regURI = /\w+:\/\/[\w\-.\/?%&=:@;]*/g;
var regXMLTag = /<\/?\w+[^>]*>/g;
var regCComment = /\/\*[\s\S]*?\*\//gm;
var regLineComment = /\/\/.*$/gm;
var regDoubleQuote = /"([^\\"\n]|\\.)*"/g; // "

/**
 * @param {number} len
 * @param {number} opt_filter
 */
function genRandomString(len, opt_filter) {
  var str = '',
      letter = '';
  if (!(opt_filter & 1)) letter += 'abcdefghijklmnopqrstuvwxyz';
  if (!((opt_filter >> 1) & 1)) letter += 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  if (!((opt_filter >> 2) & 1)) letter += '0123456789';
  if (!((opt_filter >> 3) & 1)) letter += '_';
  if (!((opt_filter >> 4) & 1)) letter += '!\"#$%&\'()=~|-^@[;:],./`{+*}>?';
  if (!((opt_filter >> 5) & 1)) letter += '(`~!@#$%^&*()_+-={}|[]\\:\";\'<>?,./)';

  for (var i = 0, range = letter.length + 1; i < len; ++i) {
    str += letter.charAt(Math.random() * range | 0);
  }

  return str;
}
