import java.io.*;
class Callme
{
synchronized void call()
 {
  System.out.print("["+"Hai");
  try{
      Thread.sleep(1000);
     }
  catch(InterruptedException e)
  {
   System.out.println("Interrupted");
  }
  System.out.println("]");
 }
}
class Caller extends Thread
{
 Callme target;
 public Caller(Callme targ)
 {
 target=targ;
 }
 public void run()
 {
  target.call();
 }
}
class Synch
{
public static void main(String args[])
{
Callme target=new Callme();
Caller ob1=new Caller(target);
Caller ob2=new Caller(target);
ob1.start();
ob2.start();
try{
    ob1.join();
    ob2.join();
    }
  catch(InterruptedException e)
  {
   System.out.println("Interrupted");
   }
  }
}
