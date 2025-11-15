import java.util.Scanner;

/**
 * Write a description of class InputReader here.
 *
 * @author (Irfan Sandy)
 * @version (1.0.0)
 */
public class InputReader
{
    private Scanner scanner;

    public InputReader() {
        scanner = new Scanner(System.in);
    }

    public String readString(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine();
    }

    public void close() {
        scanner.close();
    }
}