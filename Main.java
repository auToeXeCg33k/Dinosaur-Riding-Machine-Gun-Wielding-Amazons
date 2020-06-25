import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    boolean repeat = true;
    Scanner sc = new Scanner(System.in);
    Map<String, DinoszauruszonLovagloGepfegyveresAmazon> amazonMap = new HashMap<>();
    Map<String, Command> commandMap = new HashMap<>();
    commandMap.put("select", new Select());
    commandMap.put("exit", new Exit());
    commandMap.put("new", new New());
    commandMap.put("help", new Help());
    commandMap.put("attack", new Attack());
    while (repeat) {
      System.out.println("mi kéne ha vóna?");
      String command = sc.nextLine();
      String[] strings = command.split(" ");
      if (strings.length != 0 && !commandMap.containsKey(strings[0])) {
        System.out.println("ilyen parancs nincs is");
        continue;
      } 
      if (strings.length > 1) {
        if (strings[0].equals("help") || strings[0].equals("exit")) {
          System.out.println("mi ez az argumentumtenger more? értelmesen má");
          continue;
        } 
        if (commandMap.containsKey(strings[0]))
          ((Command)commandMap.get(strings[0])).execute(strings[1], amazonMap, (Select)commandMap.get("select")); 
        continue;
      } 
      if (strings[0].equals("help") || strings[0].equals("exit")) {
        repeat = ((Command)commandMap.get(strings[0])).execute();
        continue;
      } 
      System.out.println("more, argumentumok?");
    } 
  }
}
