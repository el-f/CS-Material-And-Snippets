// 59e1ee463d09a75a4400003b
function tco(fd) {
    const funcs = {};
    return fd.map(([$name, $args, $body]) => {
        this[$name] = (...args) => new Object({ $name, args });
        funcs[$name] = new Function(...$args, $body);
        return (...args) => {
            let r = funcs[$name](...args);
            while (r && r.$name) {
                r = funcs[r.$name](...r.args);
            }
            return r;
        };
    })
}

// ***********************
// ******** TESTS ********
// ***********************

describe('Environment check', () => {
    var Count = 0
    it('Tail Call Optimization should not be supported by the interpreter', () => {
        Test.expectError('Error expected', function () {
            'use strict'
            function X(S) {
                ++Count
                return S ? X(--S) : 'Yay'
            }
            return 'Yay' === X(1E6)
        })
    })
    console.log('Stack limit ≈ ' + Count)
})
const Do = (NPB, Pos, Arg) => {
    Pos = NPB[Pos]
    NPB = Test.randomize(NPB)
    Pos = NPB.indexOf(Pos)
    console.log(`Functions [${NPB.length}]`)
    console.log(NPB.slice(0, 20).map(([N, P, B]) => `function ${N}(${P}){${B}}`).join('\n'))
    20 < NPB.length && console.log('...')
    console.log(`Pos: ${Pos},Args : ${JSON.stringify(Arg)}`)
    return tco(NPB)[Pos](...Arg)
}
const Check = (NPB, Pos, Arg, Exp, Msg) => Test.assertDeepEquals(Do(NPB, Pos, Arg), Exp, Msg)
describe('Fixed Tests', () => {
    it('Works for simple tail recursives', () => {
        Check([['f', ['x'], 'return x?f(--x):"Yay"']], 0, [1e5], 'Yay', '(function f(x){return x?f(--x):"Yay"})(1e6) === "Yay"')
        Check([['f', ['x', 'y'], 'return 0<x?f(x-3,(y||0)+17):y%21']], 0, [1e5], 14, '(function f(x,y){return 0<x?f(x-3,(y||0)+17):y%21})(1e5) === 14')
    })
    it('Works for simple tail calls', () => {
        const FG =
            [
                ['f', ['n', 's'], 'return n ? g(--n,s || 0) : s'],
                ['g', ['n', 's'], 'if (n < 0) n = 3;return f(--n,s + n)']
            ]
        Check(FG, 0, [1e5], 2499950000, 'f(1e5) === 2499950000')
        Check(FG, 0, [1e5 + 1], 2500000001, 'f(1e5 + 1) === 2500000001')
        Check(FG, 1, [-1e5, 7], 9, 'g(-1e5,7) === 9')
    })
    it('Works for built-in functions', () => {
        var From = Date.now(), Current
        Do([['Sleep', ['x', 'n'], 'return n=n||Date.now(),n+x<=Date.now()||Sleep(x,n)']], 0, [100])
        Current = Date.now()
        Test.expect(From + 100 <= Current, `Should sleep 100ms after ${From}, it is ${Current} now`)

        var Count = Do([['f', ['x', 'c'], 'return x?f(Math.random()<.2?--x:x,1+(0|c)):c']], 0, [10000])
        Test.expect(30000 <= Count && Count <= 70000, `Count ${Count} should in range [30000,70000]`)
    })
    it('Works for errors', () => {
        var Ex
        try {
            Do([['f', ['x'], 'if(!x)throw";-)";return f(--x)']], 0, [1e5])
        }
        catch (e) { Ex = e }
        Test.assertDeepEquals(Ex, ';-)', 'Let the thrown string go')

        Test.expectError('Another error example', function () {
            Do([['f', [], 'return(function f(x){return x?f(--x):"⑤"})(1e5)']], 0, [])
        })
    })
})
const Rnd = Q => 0 | Q * Math.random()
describe('Extreme Tests', () => {
    it('Works for tail call circles', () => {
        var
            Fun = [...Array(10000)].map((_, F) => ['f' + F, ['x', 'y'], `return f${1 + F}(x,y)`]),
            Seed = '' + Date.now() + Rnd(100000),
            Repeat = 12 + Rnd(6),
            Full = Seed.repeat(Repeat),
            Length = (Full.length >> 1) + Rnd(Full.length / 2),
            Exp = Full.slice(0, Length),
            T = 100 + Rnd(100);

        Fun[0][2] = 'return x?f1(--x,y):y'
        Fun[42][2] = `return f43(x,"${Seed}")`
        Fun[T][2] = `return f${1 + T}(x,y.repeat(${Repeat}).slice(0,${Length}))`
        Fun[Fun.length - 1][2] = 'return f0(x,y)'
        Check(Fun, 0, [2], Exp, `f0(2) === "${Exp}"`)
    })
})
describe('Random Tests', () => {
    it('Works for 20 random tests', () => {
        const Pool = [() => {
            var
                NPB =
                    [
                        ['f', ['x'], 'return x<2?x:b(0,1,2,x)'],
                        ['b', ['l', 'r', 'n', 't'], 'return n<t?b(r,l+r%1e100,++n,t):l+r']
                    ],
                Go = (L, R, N, T) => {
                    for (; N < T; ++N) [L, R] = [R, L + R % 1e100]
                    return L + R
                },
                Solve = X => X < 2 ? X : Go(0, 1, 2, X),
                Wish = 1e5 + Rnd(4000);
            Check(NPB, 0, [Wish], Solve(Wish))
        }, () => {
            var
                Num = ['+[]', '++[+[]][+[]]', '!0+!""'],
                Plus = Rnd(1919),
                Minus = Rnd(893),
                Mult = Math.random(),
                NPB =
                    [
                        ['f', ['x', 'y'], `return y?o(x=[x + ${Plus},x - ${Minus},x * ${Mult}][${Num[0]}],--y):x`],
                        ['o', ['x', 'y'], `return v(x=[x + ${Plus},x - ${Minus},x * ${Mult}][${Num[1]}],y)`],
                        ['v', ['x', 'y'], `return f(x=[x + ${Plus},x - ${Minus},x * ${Mult}][${Num[2]}],y)`]
                    ],
                Init = Rnd(114514),
                Solve = (X, Y) => { for (; Y--;)X = (X + Plus - Minus) * Mult; return X },
                Wish = 1e5 + Rnd(4000);
            Check(NPB, 0, [Init, Wish], Solve(Init, Wish))
        }, () => {
            var
                From = Rnd(1000),
                NPB = [...Array(20)].map((_, F) =>
                    [
                        _ = `Lonely${From + 20 * F}Frog20015`,
                        ['x', 'n'],
                        `return n=n||Date.now(),n+x+${F}<=Date.now()||${_}(x,n)`
                    ]),
                Hero = Rnd(20),
                Wish = 30 + Rnd(50),
                From = Date.now(),
                Current;
            Do(NPB, Hero, [Wish])
            Current = Date.now()
            Test.expect(From + Hero + Wish <= Current, `Should sleep ${Hero + Wish}ms after ${From}, it is ${Current} now`)
        }, () => {
            var
                Token = '楊家有女初長成',
                NPB = [...Token].map((V, F) =>
                    [
                        'f' + F,
                        ['x'],
                        `return x?f${++F % Token.length}(--x):${V}`
                    ]),
                Hero = Rnd(Token.length),
                Wish = 1e5 + Rnd(4000),
                Ex = Token.charAt((Hero + Wish) % Token.length),
                Ce = '';

            try { Do(NPB, Hero, [Wish]) }
            catch (e) { Ce = String(e) }
            Test.expect(Ce.includes(` ${Ex} `), `Expected error contains ${Ex} should be returned but got ${Ce}`)
        }];
        [...Array(20)].forEach(() => Pool[0 | Pool.length * Math.random()]())
    })
})

Date.pipe('E4DE7952698246711A60040409F99E8C')