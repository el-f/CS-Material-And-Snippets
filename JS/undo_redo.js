function undoRedo(obj) {
    var commands = []
    var index = -1

    function add(cmd) {
        commands.splice(index + 1, commands.length - index)
        commands.push(cmd)
        index = commands.length - 1
    }

    return {
        get: function(key) {
            return obj[key]
        },
        set: function(key, value) {
            var prev = obj[key]
            var cmd = {
                exec: function() { obj[key] = value },
                undo: function() { obj[key] = prev }
            }

            add(cmd)
            cmd.exec()
        },
        del: function(key) {
            var prev = obj[key]
            var cmd = {
                exec: function() { delete obj[key] },
                undo: function() { obj[key] = prev }
            }

            add(cmd)
            cmd.exec()
        },
        undo: function() {
            var cmd = commands[index]
            if (cmd === void 0) throw new Error()

            cmd.undo()
            index--
        },
        redo: function() {
            var cmd = commands[index + 1]
            if (cmd === void 0) throw new Error()

            cmd.exec()
            index++
        }
    }
}