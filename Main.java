import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    World world = new World();
    System.out.println("segítségért írd be, hogy help");
    Scanner sc = new Scanner(System.in);
    boolean repeat = true;
    while (repeat) {
      System.out.println("na zsa parancs");
      String command = sc.nextLine();
      String[] strings = command.split(" ");
      if (strings[0].equals("")) {
        System.out.println("há azé írhatná be valamit");
        continue;
      } 
      if (!world.getCommandMap().containsKey(strings[0])) {
        System.out.println("ilyen parancs nincs is");
        continue;
      } 
      if (strings[0].equals("help") || strings[0].equals("exit")) {
        repeat = ((Command)world.getCommandMap().get(strings[0])).execute();
        continue;
      } 
      if (world.getCommandMap().containsKey(strings[0]))
        ((Command)world.getCommandMap().get(strings[0])).execute(strings, world); 
    } 
  }
}
