/**
 * Convert string format
 * @param {string} str
 * @param {number} option
 * <pre>
 *   0 to upper
 *   1 to lower
 *   2 to zenkaku
 *   3 to hankaku
 *   4 to katakana
 *   5 to hiragana
 *   6 proper
 * </pre>
 * @return {string}
 */
function strConv(str, option) {
  switch (option) {
    case 0:
      return str.toUpperCase();
    case 1:
      return str.toLowerCase();
    case 2:
      return toZenkakuKatakana(toZenkaku(str));
    case 3:
      return toHankakuKatakana(toHankaku(str));
    case 4:
      return toKatakana(str);
    case 5:
      return toHiragana(str);
    case 6:
      return proper(str);
    default:
      break;
  }
  return str;
}

/**
 * @param {string} str
 * @return {string}
 */
function toZenkaku(str) {
  return str.replace(/\\/g, '¥').replace(/ /g, '　')
      .replace(/'/g, '’').replace(/"/g, '”') // '
      .replace(/[\u0021-\u007e]/g, function(a){
        return String.fromCharCode(a.charCodeAt(0) + 0xfee0);
      });
}

/**
 * @param {string} str
 * @return {string}
 */
function toZenkakuKatakana(str) {
var conv = [], c  = '', n = 0,
    zen = "。「」、ヲァィゥェォャュョッアイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワン゛゜".split(''),
    han = "｡｢｣､ｦｧｨｩｪｫｬｭｮｯｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝﾞﾟ".split('');
  for (var i = 0, l = str.length; i < l; i++) {
    c = str.charAt(i);
    n = han.indexOf(c);
    if (n > -1) {
      c = zen[n];
    }
    conv.push(c);
  }
  return conv.join('');
}

/**
 * @param {string} str
 * @return {string}
 */
function toHankaku(str) {
  return str.replace(/¥/g, '\\').replace(/　/g, ' ')
      .replace(/’/g, '\'').replace(/”/g, '"') // '
      .replace(/[\uff01-\uff5e]/g, function(a){
        return String.fromCharCode(a.charCodeAt(0) - 0xfee0);
      });
}

/**
 * @param {string} str
 * @return {string}
 */
function toHankakuKatakana(str) {
var conv = [], c  = '', n = 0,
    zen = "。「」、ヲァィゥェォャュョッアイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワン゛゜".split(''),
    han = "｡｢｣､ｦｧｨｩｪｫｬｭｮｯｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝﾞﾟ".split('');
  for (var i = 0, l = str.length; i < l; i++) {
    c = str.charAt(i);
    n = zen.indexOf(c);
    if (n > -1) {
      c = han[n];
    }
    conv.push(c);
  }
  return conv.join('');
}

/**
 * @param {string} str
 * @return {string}
 */
function toKatakana(str) {
  return str.replace(/[\u3041-\u3096]/g, function(a){
    return String.fromCharCode(a.charCodeAt(0) + 0x60);
  });
}

/**
 * @param {string} str
 * @return {string}
 */
function toHiragana(str) {
  return str.replace(/[\u30A1-\u30F6]/g, function(a){
    return String.fromCharCode(a.charCodeAt(0) - 0x60);
  });
}

/**
 * @param {string} str
 * @return {string}
 */
function proper(str) {
  return str.replace(/(\w+)/g, function(a) {
    return a.charAt(0).toUpperCase() + a.substring(1).toLowerCase();
  });
}
