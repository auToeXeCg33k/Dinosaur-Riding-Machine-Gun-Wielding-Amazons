package commands;

import core.Player;
import core.World;
import entities.Amazon;
import java.util.Map;

public class List implements Command {
  public void execute(String[] strs, World world) {
    String string = "";
    for (Map.Entry<String, Amazon> entry : (Iterable<Map.Entry<String, Amazon>>)((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getAmazonMap().entrySet())
      string = string.concat((String)entry.getKey() + ", "); 
    if (string.equals("")) {
      System.out.println("Nincsenek amazonjaid.\n");
      return;
    } 
    System.out.println("Az amazonjaid: " + string.substring(0, string.length() - 2) + ".\n");
  }
}
