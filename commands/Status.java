package commands;

import core.Data;
import entities.Amazon;
import items.Item;
import java.util.Map;
import units.Point;
import units.Report;

public class Status implements Command {
  public Report execute(String[] strs, Data data) {
    if (strs.length != 1)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
    Amazon a = ((Select)data.getCommands().get("select")).getSelection();
    String ret = "";
    ret = ret.concat("" + Math.round(a.getHP()) + " HP-ja van.\n");
    ret = ret.concat((a.getGepFegyver() != null) ? ("A kezében egy " + ((Select)data.getCommands().get("select")).getSelection().getGepFegyver() + " van.\n") : "Nincs a kezében semmi.\n");
    ret = ret.concat(((a.getDinoszaurusz() != null) ? "Van" : "Nincs") + " dinoszaurusza.\n");
    ret = ret.concat(a.isLovagol() ? "Lovagol.\n" : "Nem lovagol.\n");
    ret = ret.concat("A(z) " + (data.getPlayerMarker() ? ("" + data.getWorld().getSize() - p.getX() + ";" + data.getWorld().getSize() - p.getX()) : ("" + p.getX() + 1 + ";" + p.getX() + 1)) + " koordinátán áll.\n");
    String temp = "";
    for (Map.Entry<Class<?>, Item[]> entry : (Iterable<Map.Entry<Class<?>, Item[]>>)a.getInventory().entrySet()) {
      for (int k = 0; k < ((Item[])entry.getValue()).length; k++) {
        if (((Item[])entry.getValue())[k] != null)
          temp = temp.concat("" + ((Item[])entry.getValue())[k] + ", "); 
      } 
    } 
    if (temp.equals(""))
      return new Report(ret.concat("Nincsenek itemjei.\n"), false); 
    return new Report(ret.concat("Az itemjei: " + temp.substring(0, temp.length() - 2) + ".\n"), false);
  }
}
