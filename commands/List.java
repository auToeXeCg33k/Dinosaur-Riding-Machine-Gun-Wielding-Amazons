package commands;

import core.Player;
import core.World;
import entities.Amazon;
import java.util.Map;

public class List implements Command {
  public void execute(String[] strs, World world) {
    System.out.print("Az amazonjaid: ");
    for (Map.Entry<String, Amazon> entry : (Iterable<Map.Entry<String, Amazon>>)((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getAmazonMap().entrySet())
      System.out.print((String)entry.getKey() + " "); 
    System.out.println("\n");
  }
}
