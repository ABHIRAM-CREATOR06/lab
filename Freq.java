import java.util.Scanner;

class Freq {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter total no of elements required in array: ");
    int n = sc.nextInt();
    int[] array = new int[n]; // Corrected 'Int' to 'int'
    System.out.println("Enter elements required in array: ");
    for (int i = 0; i < n; i++) { // Added initialization for 'i'
      array[i] = sc.nextInt(); // Added 'sc.' before 'nextInt()'
    }
    boolean[] counted = new boolean[n];
    for (int i = 0; i < n; i++) {
      if (!counted[i]) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
          if (array[i] == array[j]) {
            count++;
            counted[j] = true;
          }
        }
        System.out.println("Element in array " + array[i] + " has a frequency of " + count);
      }
    }
  }
}
