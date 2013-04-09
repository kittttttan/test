/**
 * @param {boolean} b
 * @param {string} s
 */
function assert(b, s) {
  if (!b) {
    var err = new Error(s);
    err.name = 'AssertionFailed';
    throw err;
  }
}

/**
 * Count function called time in a while
 * @param {function} f
 * @param {number=} [opt_ms=1000] Interval
 * @return {number} loops/sec
 */
function bench(f, opt_ms) {
  var b = Date.now(),
      i = 0;
  if (!opt_ms) { opt_ms = 1000; }
  for (; Date.now() - b < opt_ms; ++i) {
    f();
  }
  return i * 1000 / opt_ms;
}

// exports for node
if (typeof exports !== 'undefined') {
  exports.assert = assert;
  exports.bench = bench;
}
