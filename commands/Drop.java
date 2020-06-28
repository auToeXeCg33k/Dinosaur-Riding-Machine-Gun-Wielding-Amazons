package commands;

import core.Data;
import items.Item;

public class Drop implements Command {
  public String execute(String[] strs, Data data) {
    if (data.getMaxMoves() > data.getMoves()) {
      if (strs.length == 2) {
        if (((Select)data.getCommands().get("select")).getSelection() != null) {
          if (((Select)data.getCommands().get("select")).getSelection().getHP() > 0.0D) {
            if (data.getItems().get(strs[1]) != null) {
              Item dropped = ((Select)data.getCommands().get("select")).getSelection().dropFromInventory((Class)data.getItems().get(strs[1]));
              if (dropped != null) {
                data.tileOfSelected().addItem(dropped);
                return strs[1] + "eldobva.\n" + strs[1];
              } 
              return ((Select)data.getCommands().get("select")).getSelection().getNev() + " amazonnál nincs " + ((Select)data.getCommands().get("select")).getSelection().getNev() + ".";
            } 
            return "Olyen item, hogy " + strs[1] + ", nincs is!\n";
          } 
          return ((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él.\n";
        } 
        return "Válasszá ki valakit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
