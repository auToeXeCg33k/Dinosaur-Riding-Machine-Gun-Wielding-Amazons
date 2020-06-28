package commands;

import core.Player;
import core.World;

public class Steps implements Command {
  public void execute(String[] strs, World world) {
    System.out.println("A lehetséges lépéseid száma: " + world.getMaxCounter() - world.getMoveCounter() + ".");
    System.out.println("A spawnjaid száma: " + ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getSpawnCounter());
    System.out.println("Az élö amazonjaid száma: " + ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getActiveCounter() + ".");
    System.out.println("A hátralévö spawnjaid száma: " + Math.min(world.getActiveMax() - ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getActiveCounter(), world.getSpawnMax() - ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getSpawnCounter()) + ".\n");
  }
}
