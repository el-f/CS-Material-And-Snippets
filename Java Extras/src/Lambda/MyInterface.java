package Lambda;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public interface MyInterface {
    void printIt(String text);

    default void printUtf8To(String text, OutputStream outputStream) {
        try {
            outputStream.write(text.getBytes(StandardCharsets.UTF_8));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static void printItToSystemOut(String text) {
        System.out.println(text);
    }
}
