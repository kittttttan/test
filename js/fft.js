(function(exports){
'use strict';

if (typeof require !== 'undefined') {
  exports.Complex = require('./complex.js').Complex;
}
var Complex = exports.Complex;

var cos = Math.cos;
var sin = Math.sin;
//var PI = Math.PI;
var PI2 = -2 * Math.PI;

/**
 * Fast Fourier transform
 * @class Fft
 */
var Fft = {
  fftFloat: fftFloat,
  ifftFloat: ifftFloat,
  fft: fft,
  ifft: ifft
};

/**
 * convert number[] to Complex[].
 * @param {number[]}
 * @return {Complex[]}
 */
function fl2Comp(x) {
  var c = [];
  for (var i = 0, l = x.length; i < l; ++i) {
    c[i] = new Complex(x[i], 0.0);
  }
  return c;
}

/**
 * transform from numbers
 * @method Fft.fftFloat
 * @param {number[]} x
 * @return {Complex[]}
 */
function fftFloat(x) {
  return fft(fl2Comp(x));
}

/**
 * inverse from numbers
 * @method Fft.ifftFloat
 * @param {number[]} x
 * @return {Complex[]}
 */
function ifftFloat(x) {
  return ifft(fl2Comp(x));
}

/**
 * Fast Fourier transform
 * @method Fft.fft
 * @param {Complex[]} x
 * @return {Complex[]}
 */
function fft(x) {
  var N = x.length;
  if (N < 1 || (N & (N - 1))) {
    throw new Error("length of data must be a power of 2.");
  }
  if (N === 2) { return _fft2(x); }
  if (N === 1) { return [x[0]]; }
  return _fft(x);
}

/**
 * transform 2
 * @param {Complex[]} x x.length === 2
 * @return {Complex[]}
 */
function _fft2(x) {
  return [x[0].add(x[1]), x[0].sub(x[1])];
}

/**
 * transform 4
 * @param {Complex[]} x x.length === 4
 * @return {Complex[]}
 */
function _fft4(x) {
//  var q = _fft2([x[0], x[2]]);
//  var r = _fft2([x[1], x[3]]);
//  var wk = r[1].mul(new Complex(0, -1));
  var q = [x[0].add(x[2]), x[0].sub(x[2])];
  var r = [x[1].add(x[3]), x[1].sub(x[3])];
  var wk = new Complex(r[1]._i, -r[1]._r);

  return [
    q[0].add(r[0]),
    q[1].add(wk),
    q[0].sub(r[0]),
    q[1].sub(wk)
  ];
}

/**
 * transform
 * @param {Complex[]} x
 * @return {Complex[]}
 */
function _fft(x) {
  var N = x.length;
  if (N === 4) { return _fft4(x); }

  var N2 = N >> 1;
  
  var even = [];
//  var odd = [];
  var k = 0;
  for (; k < N2; ++k) {
    even[k] = x[k << 1];
//    odd[k] = x[(k << 1) + 1];
  }
  var q = _fft(even);
//  var r = _fft(odd);

  // reuse the array
  var odd = even;
  for (k = 0; k < N2; ++k) {
    odd[k] = x[(k << 1) + 1];
  }
  var r = _fft(odd);

  var y = [];
  var th = PI2 / N;
  var kth = 0.0;

  var wk = r[0].mul(new Complex(1, 0));
  y[0] = q[0].add(wk);
  y[N2] = q[0].sub(wk);
  
  for (k = 1; k < N2; ++k) {
    kth = k * th;
    wk = r[k].mul(new Complex(cos(kth), sin(kth)));
    y[k] = q[k].add(wk);
    y[k + N2] = q[k].sub(wk);
  }

  return y;
}

/**
 * inverse
 * @method Fft.ifft
 * @param {Complex[]} x
 * @return {Complex[]}
 */
function ifft(x) {
  var N = x.length;
  var y = [];
  var i = 0;
  for (; i < N; ++i) {
    y[i] = x[i].conj();
  }

  y = fft(y);

  var div = 1.0 / N;
  for (i = 0; i < N; ++i) {
    y[i]._r *= div;
    y[i]._i *= -div;
  }

  return y;
}

// exports
exports.Fft = Fft;

}(typeof exports !== 'undefined' ? exports : this));
