package Assignment;

import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Locale;

public class MyLogger {

    public enum LogLevel {
        INFO,
        DEBUG,
        WARN,
        ERROR,
        FATAL
    }

    public File logfile;
    public String currentClass;
    public boolean append = true;

    public static final DateTimeFormatter DATE_TIME_FORMATTER =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSS", Locale.ENGLISH);

    public static final String LOG_MESSAGE_FORMAT = "[%-5s] %s [%s] %s";


    public MyLogger(String filePath, String _class) {
        currentClass = _class;
        logfile = new File(filePath);
    }

    public void log(LogLevel level, String message) {
        String msg = String.format(
                LOG_MESSAGE_FORMAT,
                level.name(),
                LocalDateTime.now().format(DATE_TIME_FORMATTER),
                currentClass,
                message
        );
        System.out.println(msg);
        try (PrintWriter writer = new PrintWriter(new FileWriter(logfile, append))) {
            writer.println(msg);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

}
