package core;

import commands.Attack;
import commands.Command;
import commands.Drop;
import commands.End;
import commands.Equip;
import commands.Exit;
import commands.GetOff;
import commands.GetOn;
import commands.Help;
import commands.List;
import commands.LookAround;
import commands.Move;
import commands.New;
import commands.PickUp;
import commands.Select;
import commands.Status;
import commands.Steps;
import commands.Tame;
import items.GepKatana;
import items.MiniGun;
import items.Pistol;
import items.RocketLauncher;
import items.ShotGun;
import java.util.HashMap;

public class Maps {
  private HashMap<String, Command> commandMap = new HashMap<>();
  
  private HashMap<String, Class<?>> itemClassMap = new HashMap<>();
  
  private HashMap<Boolean, Player> playerMap = new HashMap<>();
  
  public Maps() {
    this.commandMap.put("select", new Select());
    this.commandMap.put("exit", new Exit());
    this.commandMap.put("new", new New());
    this.commandMap.put("help", new Help());
    this.commandMap.put("attack", new Attack());
    this.commandMap.put("move", new Move());
    this.commandMap.put("lookaround", new LookAround());
    this.commandMap.put("tame", new Tame());
    this.commandMap.put("geton", new GetOn());
    this.commandMap.put("getoff", new GetOff());
    this.commandMap.put("status", new Status());
    this.commandMap.put("pickup", new PickUp());
    this.commandMap.put("drop", new Drop());
    this.commandMap.put("equip", new Equip());
    this.commandMap.put("steps", new Steps());
    this.commandMap.put("end", new End());
    this.commandMap.put("list", new List());
    this.itemClassMap.put("pisztoly", Pistol.class);
    this.itemClassMap.put("gépkatana", GepKatana.class);
    this.itemClassMap.put("shotgun", ShotGun.class);
    this.itemClassMap.put("minigun", MiniGun.class);
    this.itemClassMap.put("rocketlauncher", RocketLauncher.class);
    this.playerMap.put(Boolean.valueOf(true), new Player());
    this.playerMap.put(Boolean.valueOf(false), new Player());
  }
  
  public HashMap<String, Command> getCommandMap() {
    return this.commandMap;
  }
  
  public HashMap<String, Class<?>> getItemClassMap() {
    return this.itemClassMap;
  }
  
  public HashMap<Boolean, Player> getPlayerMap() {
    return this.playerMap;
  }
}
