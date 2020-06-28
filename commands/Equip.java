package commands;

import core.Data;

public class Equip implements Command {
  public String execute(String[] strs, Data data) {
    if (strs.length == 2) {
      if (((Select)data.getCommands().get("select")).getSelection() != null) {
        if (((Select)data.getCommands().get("select")).getSelection().getHP() > 0.0D) {
          if (data.getItems().get(strs[1]) != null) {
            if (((Select)data.getCommands().get("select")).getSelection().equip((Class)data.getItems().get(strs[1])))
              return strs[1] + " kézbe véve.\n"; 
            return "Nincs is " + strs[1] + " az inventoryban!\n";
          } 
          return "Olyan fegyver, hogy " + strs[1] + ", nincs is!\n";
        } 
        return ((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n";
      } 
      return "Válasszá ki valakit!\n";
    } 
    return "Nem megfelelő a gyökérségek száma heló!\n";
  }
}
