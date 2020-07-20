const Express = require('express');
const BodyParser = require('body-parser');
const Crypto = require('crypto');
const Exec = require('child_process').exec;
const Fs = require('fs');

const co = require('co');

// Get environment variables.
const envTMP = process.env.TMP || '/tmp/qmk-';
const envPORT = process.env.PORT || 80;
const envQMK = '/usr/local/qmk';

// Create the express app.
const app = Express();
app.use(BodyParser.json());
app.use(BodyParser.urlencoded({ extended: true }));

// Allow cross-origin requests.
app.all('*', (req, res, next) => {
	res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
    res.header('Access-Control-Allow-Headers','Origin, X-Requested-With, Content-Type, Accept, Authorization, Access-Control-Allow-Credentials');
    res.header('Access-Control-Allow-Credentials', 'true');
	next();
});

// Set up the /build route.
app.post('/build', (req, res) => {
	// Get the files.
	const files = req.body;

	// Create a temporary directory.
	const key = Crypto.randomBytes(16).toString('hex');
    const tmpdir = envTMP + key;

	// Setup helper functions.
	const clean = () => {
		Exec('rm -rf ' + tmpdir);
	};

	const sendError = err => {
    console.error(err);
		res.json({ error: err });
		clean();
	};

	// Start.
	co(function*() {

		// Copy the base stencil.
		yield new Promise((resolve, reject) => {
			Exec('cp -rp ' + envQMK + ' ' + tmpdir, (err, stdout, stderr) => {
				if (err) return reject('Failed to initialize.');
				resolve();
			});
		});

		// Copy all the files.
		for (const file in files) {
			yield new Promise((resolve, reject) => {
				const fileName = file.replace('qmk_firmware', tmpdir);
				Fs.writeFile(fileName, files[file], err => {
					if (err) return reject('Failed to initialize.');
					resolve();
				});
			});
		}

		// Make.
		yield new Promise((resolve, reject) => {
			Exec('cd ' + tmpdir + '/keyboards/kb && make', (err, stdout, stderr) => {
				if (err) return reject(stderr);
				resolve();
			});
		});

		// Read the hex file.
		const hex = yield new Promise((resolve, reject) => {
			Fs.readFile(tmpdir + '/kb_default.hex', 'utf8', (err, data) => {
				if (err) return reject('Failed to read hex file.');
				resolve(data);
			});
		});

		// Send the hex file.
		res.json({ hex: hex });

		// Clean up.
		clean();
	}).catch(e => sendError(e));
});

// Start listening.
app.listen(envPORT, () => console.log('Listening on port ' + envPORT + '...'));
