package ktn.log;

import java.text.SimpleDateFormat;
import java.util.logging.LogRecord;

public class Formatter extends java.util.logging.Formatter {
    private static final SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");

    @Override
    public String format(LogRecord record) {
        final StringBuffer message = new StringBuffer(131);
        
        final long millis = record.getMillis();
        message.append(sdf.format(millis));
        message.append(' ');
        
        final String loggerName = record.getLoggerName();
        if (loggerName != null) {
            message.append(loggerName);
        } else {
            final String className = record.getSourceClassName();
            if (className != null) {
                message.append(className);
            }
        }
        
        final String methodName = record.getSourceMethodName();
        if (methodName != null) {
            message.append('.');
            message.append(methodName);
        }
        message.append(' ');

        message.append(record.getThreadID());
        message.append(' ');

        message.append(record.getLevel().toString());
        message.append(' ');

        message.append(formatMessage(record));
        message.append('\n');

        final Throwable throwable = record.getThrown();
        if (throwable != null) {
            message.append(throwable.toString());
            message.append('\n');
            for (StackTraceElement trace : throwable.getStackTrace()) {
                message.append('\t');
                message.append(trace.toString());
                message.append('\n');
            }
        }
        
        return message.toString();
    }
}
