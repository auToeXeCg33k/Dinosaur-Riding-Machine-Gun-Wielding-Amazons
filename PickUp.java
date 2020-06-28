import java.util.HashMap;

public class PickUp implements Command {
  private HashMap<String, Class<?>> classes;
  
  public PickUp() {
    this.classes = new HashMap<>();
    this.classes.put("pistol", Pistol.class);
    this.classes.put("katana", GepKatana.class);
    this.classes.put("shotgun", ShotGun.class);
    this.classes.put("minigun", MiniGun.class);
    this.classes.put("rocketlauncher", RocketLauncher.class);
  }
  
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (this.classes.get(strs[1]) != null) {
        for (int i = 0; i < (world.getTiles()).length; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length; j++) {
            if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
              boolean exists = false;
              for (int k = 0; k < world.getTiles()[i][j].getItemList().size(); k++) {
                if (((Class)this.classes.get(strs[1])).isInstance(world.getTiles()[i][j].getItemList().get(k))) {
                  exists = true;
                  if (!((GepFegyver)world.getTiles()[i][j].getItemList().get(k)).isHeld()) {
                    ((Select)world.getCommandMap().get("select")).getSelection().setGepfegyver((GepFegyver)world.getTiles()[i][j].getItemList().get(k));
                    System.out.println("Picked up " + strs[1]);
                    break;
                  } 
                } 
              } 
              if (!exists)
                System.out.println("ilyen fegyver itt nincs"); 
            } 
          } 
        } 
      } else {
        System.out.println("ilyen fegyver nincs is");
      } 
    } else {
      System.out.println("nem megfelelő argumentummenyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
