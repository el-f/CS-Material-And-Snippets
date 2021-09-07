package Snippets;

import lombok.experimental.UtilityClass;

import javax.script.*;

@UtilityClass
public class EvaluateExpression {

    ScriptEngineManager manager = new ScriptEngineManager();
    ScriptEngine engine = manager.getEngineByName("js");

    String eval(String expression) {
        try {
            return engine.eval(expression).toString();
        } catch (ScriptException e) {
            return null;
        }
    }

    public void main(String[] args) {
        System.out.println(eval("x = 10"));
        System.out.println(eval("y = 20"));
        System.out.println(eval("x * y"));
        System.out.println(eval("Math.pow(x, 2) + Math.pow(y, 2)"));
        System.out.println(eval("x + 2"));
        System.out.println(eval("1 / 4 + Math.sqrt(25)"));
        System.out.println(eval("3 ^ 4"));

        long x = 1000;
        System.out.println(Double.parseDouble(eval("0.5 + 0.5 * 0.5")) * 11 + x);
    }

}
