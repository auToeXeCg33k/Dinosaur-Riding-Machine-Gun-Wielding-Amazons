package core;

import commands.Command;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    World world = new World();
    Tracker tracker = new Tracker();
    System.out.println("A parancsok listájáért, és egy kis howtoplayért írd be a help parancsot!\n");
    Scanner sc = new Scanner(System.in);
    while (true) {
      System.out.println("Player " + (world.getActivePlayer() ? "2" : "1") + " parancsa:");
      String command = sc.nextLine();
      String[] strings = command.split(" ");
      if (strings[0].equals("")) {
        System.out.println("Há, azé írhatná be valamit...\n");
        continue;
      } 
      if (!world.getCommandMap().containsKey(strings[0])) {
        System.out.println("Ilyen parancs nincs is bruh!\n");
        continue;
      } 
      ((Command)world.getCommandMap().get(strings[0])).execute(strings, world);
      tracker.track(world);
    } 
  }
}
