import java.util.Scanner;

class Palin {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a string:");
        String str = sc.nextLine().toLowerCase();
        int length = str.length();
        int st = 0;
        int en = length - 1;
        while (st <= en) {
            if (str.charAt(st) != str.charAt(en)) {
                break;
            }
            else {
                st++;
                en--;
            }
        }
        if (st >= en) {
            System.out.println("Palindrome");
        }
        else {
            System.out.println("Not Palindrome");
        }
    }
}
