// 574d0b01b4b769b207000ca3

const inject = (before, fn) => function() {
    before.apply(this, arguments);
    return fn.apply(this, arguments);
}

class Wand {
    constructor(funcs = {}) {
        Object.assign(this, funcs);
        this.history    = [];
        this.recent     = () => this.history;
        this.clear      = () => this.history = ['clear'];
        this.memento    = (func, funcName) => inject(() => this.history.unshift(funcName), func);
        
        return new Proxy(this, {
            get: (target, property) => {
                const value = target[property];
                return (value instanceof Function) ? this.memento(value, property) : value;
            }
        });
    }
}