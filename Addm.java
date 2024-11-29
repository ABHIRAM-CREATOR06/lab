import java.util.Scanner;

// Matrix Addition
public class Addm {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input the number of rows and columns
        System.out.println("Enter the number of rows: ");
        int rows = sc.nextInt();
        System.out.println("Enter the number of columns: ");
        int cols = sc.nextInt();

        // Initialize matrices
        int[][] matrixA = new int[rows][cols];
        int[][] matrixB = new int[rows][cols];

        // Input elements of matrix A
        System.out.println("Enter elements of matrix A:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrixA[i][j] = sc.nextInt();
            }
        }

        // Input elements of matrix B
        System.out.println("Enter elements of matrix B:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrixB[i][j] = sc.nextInt();
            }
        }

        // Initialize the result matrix
        int[][] resultMatrix = new int[rows][cols];

        // Add the matrices
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }

        // Print the result matrix
        System.out.println("Result of Matrix Addition:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(resultMatrix[i][j] + " ");
            }
            System.out.println();
        }

        sc.close();
    }
}
