package commands;

import core.Data;
import core.Report;
import items.Item;

public class PickUp implements Command {
  public Report execute(String[] strs, Data data) {
    if (data.getMaxMoves() == data.getMoves())
      return new Report("Nincs több lépésed.\n", false); 
    if (strs.length != 2)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n", false); 
    if (data.getItems().get(strs[1]) == null)
      return new Report("Olyan item, hogy " + strs[1] + " nincs is.\n", false); 
    for (int k = 0; k < data.tileOfSelected().getItemList().size(); k++) {
      if (((Item)data.tileOfSelected().getItemList().get(k)).getClass().equals(data.getItems().get(strs[1]))) {
        if (((Select)data.getCommands().get("select")).getSelection().putInInventory(data.tileOfSelected().getItemList().get(k))) {
          data.tileOfSelected().remove(data.tileOfSelected().getItemList().get(k));
          String ret = strs[1] + " felvéve.\n";
          return new Report(ret.concat(data.nextMove()), false);
        } 
        return new Report("Nem sikerült felvenni.\n", false);
      } 
    } 
    return new Report(strs[1] + " nincs is a közelben.\n", false);
  }
}
