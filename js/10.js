// ES10 - ECMAScript 2019 examples

assert_eq([ 0, [ 1 ] ].flat(), [0, 1])

assert_eq([ 0, [ 1, [ 2 ] ] ].flat(), [ 0, 1, [ 2 ] ])

assert_eq([ 0, [ 1, [ 2 ] ] ].flat(Infinity), [ 0, 1, 2 ])

assert_eq([ 0, 2 ].flatMap(x => [x, x + 1]), [ 0, 1, 2, 3 ])

assert_eq(" a ".trimStart().trimEnd(), "a")

try  { } catch /* Optional Catch Binding */ { }

assert_eq(Object.fromEntries([['1', 2], ['3', 4]]), { '1': 2, '3': 4 })

assert_eq((function () { }).toString(), 'function () { }')

assert_eq(String(Symbol(1)), 'Symbol(1)')

assert_eq(Symbol(1).description, '1')

assert_eq(JSON.stringify('\uD800'), '"\\ud800"')

/*
 References
 https://alligator.io/js/es2019/
 https://blog.logrocket.com/5-es2019-features-you-can-use-today/
 https://firstclassjs.com/ecmascript-2019es2019-new-features-with-examples/
 https://medium.com/@selvaganesh93/javascript-whats-new-in-ecmascript-2019-es2019-es10-35210c6e7f4b
*/

