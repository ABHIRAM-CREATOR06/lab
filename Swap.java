import java.util.*;
public class Swap{
  public static void main(String[]args){
    Scanner sc=new Scanner(System.in);
    System.out.println("enter element no 1:");
    int m=sc.nextInt();
    System.out.println("enter element no 2:");
    int n=sc.nextInt();
    int temp;
    temp=m;
    m=n;
    n=temp;
    System.out.println("After swapping");
    System.out.println("enter element in no1: "+m);
    System.out.println("enter element in no 2: "+n);
  }
}
