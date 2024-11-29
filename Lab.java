
import java.util.Random;

class Even extends Thread {
    private int num;
    public Even(int num) {
        this.num = num;
    }
    public void run() {
        System.out.println("Square of " + num + " is " + (num * num));
    }
}
class Odd extends Thread {
    private int num;
    public Odd(int num) {
        this.num = num;
    }
    public void run() {
        System.out.println("Cube of " + num + " is " + (num * num * num));
    }
}
class RandomNumberGenerator extends Thread {
    public void run() {
        Random r = new Random();
        for (int i = 0; i <= 10; i++) {
            int num = r.nextInt(100);
            if (num % 2 == 0) {
                System.out.println("Even Thread start");
                new Even(num).start();
            } else {
                System.out.println("Odd Thread invoked");
                new Odd(num).start();
            }
        }
    }
}
public class Lab {
    public static void main(String[] args) {
        RandomNumberGenerator rng = new RandomNumberGenerator();
        rng.start();
    }
}
