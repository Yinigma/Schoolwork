import java.util.ArrayList;

/**
 * Class EthernetPlayer
 */

public class EthernetPlayer extends MusicPlayer {

	private int deviceID;
	private int connStatus;

	static final int CONNECTED = 1;
	static final int NOT_CONNECTED = 0;

	private ArrayList<String> downloadList = new ArrayList<String>();

	public EthernetPlayer(int id) {
		super();
		deviceID = id;
		connStatus = NOT_CONNECTED;

		downloadList.add("Dark Horse");
		downloadList.add("Royals");
		downloadList.add("Counting Stars");
		downloadList.add("Let Her Go");
		downloadList.add("The Fox");
		System.out.println("Creating EthernetPlayer: " + deviceID);
	}

	/**
	 * @override turnOn
	 *
	 */

	public void turnOn() {

		System.out.println("EthernetPlayer Powering ON");
		this.status = ON;
		this.connectToNetwork();

	}

	/**
	 * Connect to network
	 *
	 */

	public void connectToNetwork() {

		if (this.status == OFF) {

		}

		else if (connStatus == CONNECTED) {
			System.out.println("Already Connected");
		} else {
			connStatus = CONNECTED;
			System.out.println("Connected to Network");
			System.out.println();
		}

	}

	/**
	 * @override play
	 *
	 */

	public void play(int trackNumber) {
		if (trackNumber < 0 || trackNumber >= this.PLAYLIST_SIZE
				|| trackNumber >= this.playlist.size()) {
			System.out.println("Please enter valid trackNo. " + trackNumber
					+ " Invalid!");
			this.status = OFF;
			return;
		}
		System.out.println("Now Playing: " + playlist.get(trackNumber));
		this.status = OFF;

	}

	/**
	 * addTrackToPlaylist: Adds mentioned track to the end of playlist array
	 *
	 */

	public void addToPlaylist(String trackName) throws ExceedsCapacityException {

		if (playlist.size() == MusicPlayer.PLAYLIST_SIZE) {
			throw new ExceedsCapacityException("Exceeds Capacity!");

		}
		playlist.add(trackName);

	}

	/**
	 * deleteFromPlaylist: deletes track of give name from the playlist
	 *
	 */

	public void deleteFromPlaylist(String trackName)
			throws TrackNotFoundException {
		boolean noDel = true;
		for (int i = 0; i < playlist.size(); i++) {
			if (playlist.get(i).equals(trackName)) {
				playlist.remove(i);
				noDel = false;
			}
		}
		if (noDel) {
			throw new TrackNotFoundException("No such track!");
		}
	}

	/**
	 * download: Downloads mentioned song from the given Download list and adds
	 * to playlist
	 *
	 */

	public void download(String trackName) {

		if (playlist.size() == PLAYLIST_SIZE) {
			System.out.println("Sorry, Playlist is full! ");
			return;
		}
		for (int i = 0; i < downloadList.size(); i++) {
			if (trackName.equals(downloadList.get(i))) {
				System.out.println("Downloading..." + trackName);
				playlist.add(trackName);
				return;
			}
		}
		System.out
				.println("Sorry, we currently do not support the track you tried to download!");
	}

}
