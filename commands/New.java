package commands;

import core.Player;
import core.World;

public class New implements Command {
  public void execute(String[] strs, World world) {
    if (world.getMoveCounter() < world.getMaxCounter()) {
      if (strs.length == 2) {
        if (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getAmazonMap().containsKey(strs[1])) {
          System.out.println(strs[1] + " már létezik.\n");
          return;
        } 
        if (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getSpawnCounter() < world.getSpawnMax() && ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getActiveCounter() < world.getActiveMax()) {
          world.newAmazon(strs[1]);
          ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).incSpawn();
          ((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).incActive();
          System.out.println(strs[1] + " létrehozva.\n");
          world.incCounter();
          return;
        } 
        System.out.println("Elfogyott a spawn more!\n");
        return;
      } 
      System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
      return;
    } 
    System.out.println("Nincs több lépésed.\n");
  }
}
