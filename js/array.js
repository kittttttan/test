/**
 * @param {Object} o
 * @return {boolean}
 */
function isArray(o) {
  return Object.prototype.toString.call(o) === '[object Array]';
}

/**
 * @param {Array} a
 * @param {function} f
 * @return {boolean}
 */
function some(a, f) {
  var i = a.length;
  while (i) {
    if (f(a[--i])) {
      return true;
    }
  }
  return false;
}

/**
 * @param {Array} a
 * @param {function} f
 * @return {boolean}
 */
function every(a, f) {
  var i = a.length;
  while (i) {
    if (!f(a[--i])) {
      return false;
    }
  }
  return true;
}

/**
 * @param {Array} a
 * @param {function} f
 * @return {function}
 */
function filter(a, f) {
  var aNew = [];
  for (var i = 0, l = a.length; i < l; ++i) {
    if (func(aNew[i])) {
      aNew.push(a[i]);
    }
  }
  return aNew;
}

/**
 * @param {Array} a
 * @param {function} f
 */
function forEach(a, f) {
  for (var i = 0, l = a.length; i < l; ++i) {
    f(a[i]);
  }
}

/**
 * @param {Array} a
 * @param {function} f
 * @return {Array}
 */
function map(a, f) {
  var n = [], i = a.length;
  while (--i) {
    n[i] = f(a[i]);
  }
  return n;
}

/**
 * @param {Array} a
 * @param {function} f
 * @return {Array}
 */
function reduce(a, f) {
  var out = a[0];
  for (var i = 1, l = a.length; i < l; ++i) {
    out = f(out, a[i]);
  }
  return out;
}

/**
 * @param {Array} a
 * @param {function} f
 * @return {Array}
 */
function reduceRight(a, f) {
  var i = a.length - 1, out = a[i];
  while (i) {
    out = f(out, a[--i]);
  }
  return out;
}

/**
 * @param {Array.<number>} a
 * @return {number}
 */
function sum(a) {
  var s = 0;
  for (var i = 0, l = a.length; i < l; ++i) {
    s += a[i];
  }
  return s;
}

/**
 * @param {Array.<number>} a
 * @return {number}
 */
function average(a) {
  var s = 0, l = a.length;
  for (var i = 0; i < l; ++i) {
    s += a[i];
  }
  return s / parseFloat(l);
}

/**
 * @param {Array} a
 * @return {Array}
 */
function unique(a) {
  var b = [];
  for (var i = 0, l = a.length; i < l; ++i) {
    if (b.indexOf(a[i]) < 0) { b.push(a[i]); }
  }
  return b;
}

/**
 * @param {number} start
 * @param {number} opt_last
 * @param {number} opt_step
 */
function range(start, opt_last, opt_step) {
  var a = [], i;
  if (arguments.length === 1) {
    opt_last = start;
    start = 0;
  }
  if (start > opt_last) {
    if (opt_step > 0) { return a; }
    if (!opt_step) { step = -1; }
    for (i = start; i > opt_last; i += opt_step) {
      a.push(i);
    }
  } else {
    if (opt_step < 0) { return a; }
    if (!opt_step) { opt_step = 1; }
    for (i = start; i < opt_last; i += opt_step) {
      a.push(i);
    }
  }
  
  return a;
}

// exports for node
if (typeof module !== 'undefined' && typeof module.exports !== 'undefined') {
  module.exports.isArray = isArray;
  module.exports.some = some;
  module.exports.every = every;
  module.exports.filter = filter;
  module.exports.forEach = forEach;
  module.exports.map = map;
  module.exports.reduce = reduce;
  module.exports.reduceRight = reduceRight;
  module.exports.sum = sum;
  module.exports.average = average;
  module.exports.unique = unique;
  module.exports.range = range;
}
