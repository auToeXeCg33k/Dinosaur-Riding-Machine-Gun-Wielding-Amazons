package core;

import java.util.Map;
import java.util.Scanner;

public class Tracker {
  public void track(World world) {
    for (Map.Entry<Boolean, Player> entry : world.getPlayerMap().entrySet()) {
      if (((Player)entry.getValue()).getSpawnCounter() == world.getSpawnMax() && ((Player)entry.getValue()).getActiveCounter() == 0) {
        System.out.println("\n---A játéknak vége! A nyertes: Player " + (((Boolean)entry.getKey()).booleanValue() ? "1" : "2! GG---\n"));
        System.out.println("A kilépéshez nyomj entert!");
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
        System.exit(0);
      } 
    } 
  }
}
