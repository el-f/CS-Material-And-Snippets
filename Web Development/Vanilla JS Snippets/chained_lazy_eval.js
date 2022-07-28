// 583353eab189a5b860000049
function chainedLazy(arg) {
    funcs = [];
    return {
        invoke(name, ...args) {
            funcs.push({ name, args });
            return this;
        },
        value() {
            return funcs.reduce((result, func) => {
                return result[func.name](...func.args);
            }, arg);
        }
    }
}