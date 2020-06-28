package commands;

import core.World;
import items.Item;
import java.util.Map;

public class Status implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null)
        for (int i = 0; i < (world.getTiles()).length; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length; j++) {
            if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
              System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " a neve.");
              System.out.println("" + Math.round(((Select)world.getCommandMap().get("select")).getSelection().getHP()) + " HP-ja van.");
              System.out.println((((Select)world.getCommandMap().get("select")).getSelection().getGepFegyver() != null) ? ("A kezében egy " + ((Select)world.getCommandMap().get("select")).getSelection().getGepFegyver() + " van.") : "Nincs a kezében semmi");
              System.out.println(((((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null) ? "Van" : "Nincs") + " dinoszaurusza.");
              System.out.println(((Select)world.getCommandMap().get("select")).getSelection().isLovagol() ? "Lovagol." : "Nem lovagol.");
              System.out.println("A(z) " + (world.getActivePlayer() ? ("" + world.getY() - j + ";" + world.getY() - j) : ("" + j + 1 + ";" + j + 1)) + " koordinátán áll.");
              String string = "";
              for (Map.Entry<Class<?>, Item[]> entry : (Iterable<Map.Entry<Class<?>, Item[]>>)((Select)world.getCommandMap().get("select")).getSelection().getInventory().entrySet()) {
                for (int k = 0; k < ((Item[])entry.getValue()).length; k++) {
                  if (((Item[])entry.getValue())[k] != null)
                    string = string.concat("" + ((Item[])entry.getValue())[k] + ", "); 
                } 
              } 
              if (string.equals("")) {
                System.out.println("Nincsenek itemjei.\n");
                return;
              } 
              System.out.println("Az itemjei: " + string.substring(0, string.length() - 2) + ".\n");
              return;
            } 
          } 
        }  
      System.out.println("Válasszá ki valakit!\n");
      return;
    } 
    System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
  }
}
