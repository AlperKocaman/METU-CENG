public class Logger {
    private static long startTime;

    public static void InitLogger() {
        startTime = System.nanoTime();
    }

    public static synchronized void LogSuccessfulReservation(String name, String seats, long time) {
        long currentThreadID = Thread.currentThread().getId();
        long timestamp = time - startTime;
        System.out.printf("[*] %012.5f | %d | %s | %s |\n", timestamp / 1000000.0, currentThreadID, name, seats);
    }

    public static synchronized void LogSuccessfulReservation(String name, String seats, long time, String comment) {
        long currentThreadID = Thread.currentThread().getId();
        long timestamp = time - startTime;
        System.out.printf("[*] %012.5f | %d | %s | %s | Comment: %s\n", timestamp / 1000000.0, currentThreadID, name, seats, comment);
    }

    public static synchronized void LogFailedReservation(String name, String seats, long time) {
        long currentThreadID = Thread.currentThread().getId();
        long timestamp = time - startTime;
        System.out.printf("[X] %012.5f | %d | %s | %s |\n", timestamp / 1000000.0, currentThreadID, name, seats);
    }

    public static synchronized void LogFailedReservation(String name, String seats, long time, String comment) {
        long currentThreadID = Thread.currentThread().getId();
        long timestamp = time - startTime;
        System.out.printf("[X] %012.5f | %d | %s | %s | Comment: %s\n", timestamp / 1000000.0, currentThreadID, name, seats, comment);
    }

    public static synchronized void LogDatabaseFailiure(String name, String seats, long time) {
        long currentThreadID = Thread.currentThread().getId();
        long timestamp = time - startTime;
        System.out.printf("[-] %012.5f | %d | %s | %s |\n", timestamp / 1000000.0, currentThreadID, name, seats);
    }
    public static synchronized void LogDatabaseFailiure(String name, String seats, long time, String comment) {
        long currentThreadID = Thread.currentThread().getId();
        long timestamp = time - startTime;
        System.out.printf("[-] %012.5f | %d | %s | %s | Comment: %s\n", timestamp / 1000000.0, currentThreadID, name, seats, comment);
    }


}
