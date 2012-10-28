/**
 * sprintf
 * @param {string} str
 * @return {string}
 */
function sprintf(str) {
  var argv = arguments,
      index = 1;
  return str.replace(
    /%([+\-#0])?(\d+)?(?:\.(\d+))?([%defoxs])/g,
    function(src, flag, width, prec, type) {
      if (type === '%') { return '%'; }
      var s = '', n = 0;
      if (type === 's') {
        s = argv[index];
      }
      else if (type === 'd') {
        n = argv[index] | 0;
        s = (flag === '+' && n > 0 ? '+' : '') + n;
      }
      else if (type === 'o') {
        n = argv[index] | 0;
        s = (flag === '+' && n > 0 ? '+' : '') +
            (flag === '#' ? '0' : '') + (n).toString(8);
      }
      else if (type === 'x') {
        n = argv[index] | 0;
        s = (flag === '+' && n > 0 ? '+' : '') +
            (flag === '#' ? '0x' : '') + (n).toString(16);
      }
      else if (type === 'e') {
        s = (flag === '+' && argv[index] > 0 ? '+' : '') +
            (prec ? argv[index].toExponential(prec) : argv[index].toString());
      }
      else if (type === 'f') {
        s = (flag === '+' && argv[index] > 0 ? '+' : '') +
            (prec ? argv[index].toFixed(prec) : argv[index].toString());
      }
      ++index;
      if (width > s.length) {
        var prefix = repeatString((flag === '0' ? '0': ' '), width);
        if (flag === '-') {
          s += prefix;
        } else {
          s = prefix + s;
        }
        return s.slice(-width);
      }
      return s;
    });
}

/**
 * repeat string
 * @param {string} str
 * @param {number} repeat
 * @return {string}
 */
function repeatString(str, repeat) {
  var result = '';
  for (; repeat > 0; repeat >>= 1, str += str) {
    if (repeat & 1) {
      result += str;
    }
  }
  return result;
}

// exports for node
if (typeof module !== 'undefined' && typeof module.exports !== 'undefined') {
  module.exports.sprintf = sprintf;
  module.exports.repeatString = repeatString;
}
