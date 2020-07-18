const React = require('react');

const Display = require('ui/display');
const Panes = require('ui/panes');

class Editor extends React.Component {

	constructor(props) {
		super(props);

		// Initialize notification for leaving page.
		window.onbeforeunload = () => {
			return '你确定要离开本页面?所有未保存进度将丢失';
		};
	}

	render() {
		return <div>
			<Display
				state={ this.props.state }/>
			<Panes
				state={ this.props.state }/>
		</div>;
	}

}

module.exports = Editor;
