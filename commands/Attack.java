package commands;

import core.Data;
import core.Player;

public class Attack implements Command {
  public String execute(String[] strs, Data data) {
    if (data.getMaxMoves() > data.getMoves()) {
      if (strs.length == 2) {
        if (((Select)data.getCommands().get("select")).getSelection() != null) {
          if (((Select)data.getCommands().get("select")).getSelection().getHP() != 0.0D) {
            if (((Select)data.getCommands().get("select")).getSelection().getGepFegyver() != null) {
              if (((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).hasAmazon(strs[1])) {
                if (data.tileOfSelected().containsAmazon(((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]))) {
                  if (((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]).getHP() != 0.0D) {
                    String ret = ((Select)data.getCommands().get("select")).getSelection().tamad(((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1])) + ((Select)data.getCommands().get("select")).getSelection().tamad(((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]));
                    if (((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).getAmazon(strs[1]).getHP() == 0.0D)
                      ((Player)data.getPlayers().get(Boolean.valueOf(!data.getPlayerMarker()))).decActive(); 
                    return ret;
                  } 
                  return strs[1] + " is nem él.\n";
                } 
                return strs[1] + " nincs is rangeben.\n";
              } 
              return strs[1] + " nem is létezik.\n";
            } 
            return "Nem tok durrogtatni, fasse fogok.\n";
          } 
          return ((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él.\n";
        } 
        return "Válasszá valami buzit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
