/**
 * Standard output
 * @param {string} s Output message
 */
function stdout(s) {
  if (typeof window !== 'undefined'
      && typeof window.document !== 'undefined') {
    document.writeln(s);
  }
  else if (typeof WScript !== 'undefined') {
    WScript.echo(s);
  }
  else if (typeof console !== 'undefined') {
    console.log(s);
  }
  else if (typeof print !== 'undefined') {
    print(s);
  }
}

/**
 * @param {boolean} b
 * @param {string} s
 * @see stdout
 */
function assert(b, s) {
  if (!b) { throw s; }
}

/**
 * Count function called time in a while
 * @param {function} f
 * @param {number=} opt_ms Interval. default is 1000.
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

/**
 * Load script
 * @param {string} src Path to script file
 * @param {function=} opt_callback
 */
function loadScript(src, opt_callback) {
  var head = document.getElementsByTagName('head')[0],
      script = document.createElement('script'),
      done = false;
  script.setAttribute('src', src);
  script.onload = script.onreadstatechange = function() {
    if (!done && (!this.readyState || this.readyState === 'loaded'
        || this.readyState === 'complete')) {
      done = true;
      script.onload = script.onreadystatechange = null;
      if (opt_callback) {
        opt_callback();
      }
    }
  }
  head.insertBefore(script, head.firstChild);
}
