import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    boolean repeat = true;
    Scanner sc = new Scanner(System.in);
    Map<String, DinoszauruszonLovagloGepfegyveresAmazon> objMap = new HashMap<>();
    while (repeat) {
      String name;
      System.out.println("What do you want to do?");
      String command = sc.nextLine();
      switch (command) {
        case "exit":
          System.out.println("Exiting...");
          repeat = false;
          continue;
        case "new":
          System.out.println("Name of new entity?");
          name = sc.nextLine();
          if (objMap.containsKey(name)) {
            System.out.println("An entity with this name already exists.");
            continue;
          } 
          objMap.put(name, new DinoszauruszonLovagloGepfegyveresAmazon(name, true, true, true));
          continue;
        case "select":
          System.out.println("Select whom?");
          name = sc.nextLine();
          if (objMap.containsKey(name)) {
            System.out.println(name + " selected.");
            System.out.println("What would you like this entity to do?");
            command = sc.nextLine();
            switch (command) {
              case "attack":
                System.out.println("Attack whom?");
                command = sc.nextLine();
                if (objMap.containsKey(command)) {
                  ((DinoszauruszonLovagloGepfegyveresAmazon)objMap.get(name)).tamad(objMap.get(command));
                  continue;
                } 
                System.out.println("There's no entity with the given name.");
                continue;
            } 
            continue;
          } 
          System.out.println("No entity exists with the given name.");
          continue;
        case "help":
          System.out.println("Possible commands:");
          System.out.println("exit: quit the game.");
          System.out.println("new: create new entity.");
          System.out.println("select: choose an entity to give command to.");
          System.out.println("attack: after selecting an entity, you can command the entity to attack another one.");
          continue;
      } 
      System.out.println("Unknown command. To get a list of the available commands, type 'help'.");
    } 
  }
}
