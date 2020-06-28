package commands;

import core.Data;
import entities.Amazon;
import java.util.Map;

public class List implements Command {
  public String execute(String[] strs, Data data) {
    String string = "";
    for (Map.Entry<String, Amazon> entry : (Iterable<Map.Entry<String, Amazon>>)data.getActivePlayer().getAmazonMap().entrySet())
      string = string.concat((String)entry.getKey() + ", "); 
    if (string.equals(""))
      return "Nincsenek amazonjaid.\n"; 
    return "Az amazonjaid: " + string.substring(0, string.length() - 2) + ".\n";
  }
}
