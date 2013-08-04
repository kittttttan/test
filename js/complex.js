(function(exports){
'use strict';

/**
 * Complex
 * @class Complex
 */
function Complex(r, i) {
  this._r = +r;
  this._i = +i;
};

Complex.prototype = {
//  constructor: Complex,
//  toString: function() {
//    return '(' + this._r + '+' + this._i +'J)';
//  },
//  clone: function() {
//    return new Complex(this._r, this._i);
//  },
//  scale: function(a) {
//    return new Complex(this._r * a, this._i * a);
//  },
  /**
   * @method Complex#conjugate
   * @return {Complex}
   */
  conj: function() {
    return new Complex(this._r, -this._i);
  },
  /**
   * @method Complex#add
   * @param {Complex} a
   * @return {Complex}
   */
  add: function(a) {
    return new Complex(this._r + a._r, this._i + a._i);
  },
  /**
   * @method Complex#sub
   * @param {Complex} a
   * @return {Complex}
   */
  sub: function(a) {
    return new Complex(this._r - a._r, this._i - a._i);
  },
  /**
   * @method Complex#mul
   * @param {Complex} a
   * @return {Complex}
   */
  mul: function(a) {
    return new Complex(this._r * a._r - this._i * a._i,
        this._r * a._i + this._i * a._r);
  }
};

// exports
exports.Complex = Complex;

}(typeof exports !== 'undefined' ? exports : this));
