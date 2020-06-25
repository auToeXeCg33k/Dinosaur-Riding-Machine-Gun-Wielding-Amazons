import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    WorldGen generator = new WorldGen();
    World world = generator.createWorld();
    System.out.println("have fun! for some help, type... well... i guess... help....");
    Scanner sc = new Scanner(System.in);
    boolean repeat = true;
    while (repeat) {
      System.out.println("na zsa parancs");
      String command = sc.nextLine();
      String[] strings = command.split(" ");
      if (strings.length != 0 && !world.getCommandMap().containsKey(strings[0])) {
        System.out.println("ilyen parancs nincs is");
        continue;
      } 
      if (strings.length > 1) {
        if (strings[0].equals("help") || strings[0].equals("exit")) {
          System.out.println("mi ez az argumentumtenger more? értelmesen má");
          continue;
        } 
        if (world.getCommandMap().containsKey(strings[0]))
          ((Command)world.getCommandMap().get(strings[0])).execute(strings, world); 
        continue;
      } 
      if (strings[0].equals("help") || strings[0].equals("exit")) {
        repeat = ((Command)world.getCommandMap().get(strings[0])).execute();
        continue;
      } 
      System.out.println("more, argumentumok?");
    } 
  }
}
