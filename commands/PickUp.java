package commands;

import core.Data;
import items.Item;

public class PickUp implements Command {
  public String execute(String[] strs, Data data) {
    if (data.getMaxMoves() > data.getMoves()) {
      if (strs.length == 2) {
        if (((Select)data.getCommands().get("select")).getSelection() != null) {
          if (((Select)data.getCommands().get("select")).getSelection().getHP() > 0.0D) {
            if (data.getItems().get(strs[1]) != null) {
              for (int k = 0; k < data.tileOfSelected().getItemList().size(); k++) {
                if (((Item)data.tileOfSelected().getItemList().get(k)).getClass().equals(data.getItems().get(strs[1]))) {
                  if (((Select)data.getCommands().get("select")).getSelection().putInInventory(data.tileOfSelected().getItemList().get(k))) {
                    data.tileOfSelected().rmItem(data.tileOfSelected().getItemList().get(k));
                    String ret = strs[1] + " felvéve.\n";
                    return ret.concat(data.nextMove());
                  } 
                  return "Nem sikerült felvenni.\n";
                } 
              } 
              return strs[1] + " nincs is a közelben.\n";
            } 
            return "Olyan item, hogy " + strs[1] + " nincs is.\n";
          } 
          return ((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n";
        } 
        return "Válasszá ki valakit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
