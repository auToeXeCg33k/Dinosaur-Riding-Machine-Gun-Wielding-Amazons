package commands;

import core.Data;
import items.Item;
import java.util.Map;

public class Status implements Command {
  public String execute(String[] strs, Data data) {
    if (strs.length == 1) {
      if (((Select)data.getCommands().get("select")).getSelection() != null)
        for (int i = 0; i < (data.getWorld().getTiles()).length; i++) {
          for (int j = 0; j < (data.getWorld().getTiles()[0]).length; j++) {
            if (data.getWorld().getTiles()[i][j].containsAmazon(((Select)data.getCommands().get("select")).getSelection())) {
              String ret = "";
              ret = ret.concat(((Select)data.getCommands().get("select")).getSelection().getNev() + " a neve.\n");
              ret = ret.concat("" + Math.round(((Select)data.getCommands().get("select")).getSelection().getHP()) + " HP-ja van.\n");
              ret = ret.concat((((Select)data.getCommands().get("select")).getSelection().getGepFegyver() != null) ? ("A kezében egy " + ((Select)data.getCommands().get("select")).getSelection().getGepFegyver() + " van.\n") : "Nincs a kezében semmi.\n");
              ret = ret.concat(((((Select)data.getCommands().get("select")).getSelection().getDinoszaurusz() != null) ? "Van" : "Nincs") + " dinoszaurusza.\n");
              ret = ret.concat(((Select)data.getCommands().get("select")).getSelection().isLovagol() ? "Lovagol.\n" : "Nem lovagol.\n");
              ret = ret.concat("A(z) " + (data.getPlayerMarker() ? ("" + data.getWorld().getSize() - j + ";" + data.getWorld().getSize() - j) : ("" + j + 1 + ";" + j + 1)) + " koordinátán áll.\n");
              String temp = "";
              for (Map.Entry<Class<?>, Item[]> entry : (Iterable<Map.Entry<Class<?>, Item[]>>)((Select)data.getCommands().get("select")).getSelection().getInventory().entrySet()) {
                for (int k = 0; k < ((Item[])entry.getValue()).length; k++) {
                  if (((Item[])entry.getValue())[k] != null)
                    temp = temp.concat("" + ((Item[])entry.getValue())[k] + ", "); 
                } 
              } 
              if (temp.equals(""))
                return ret.concat("Nincsenek itemjei.\n"); 
              return ret.concat("Az itemjei: " + temp.substring(0, temp.length() - 2) + ".\n");
            } 
          } 
        }  
      return "Válasszá ki valakit!\n";
    } 
    return "Nem megfelelő a gyökérségek száma heló!\n";
  }
}
