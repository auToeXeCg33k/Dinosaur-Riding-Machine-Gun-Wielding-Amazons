package commands;

import core.Data;
import core.Player;
import core.Report;

public class Attack implements Command {
  public Report execute(String[] strs, Data data) {
    if (data.getMaxMoves() == data.getMoves())
      return new Report("Nincs több lépésed.\n", false); 
    if (strs.length != 2)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá valami buzit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él.\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getGepFegyver() == null)
      return new Report("Nem tok durrogtatni, fasse fogok.\n", false); 
    if (!((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).hasAmazon(strs[1]))
      return new Report(strs[1] + " nem is létezik.\n", false); 
    if (!data.tileOfSelected().contains(((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1])))
      return new Report(strs[1] + " nincs is rangeben.\n", false); 
    if (((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]).getHP() == 0.0D)
      return new Report(strs[1] + " is nem él.\n", false); 
    String ret = ((Select)data.getCommands().get("select")).getSelection().tamad(((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1])) + ((Select)data.getCommands().get("select")).getSelection().tamad(((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]));
    if (((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]).getHP() == 0.0D)
      ((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).decActive(); 
    return new Report(ret, false);
  }
}
