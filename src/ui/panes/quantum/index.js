const React = require('react');

const CodeMirror = require('react-codemirror');
require('codemirror/mode/clike/clike');

const C = require('const');

class Quantum extends React.Component {

	render() {
		const state = this.props.state;
		const keyboard = state.keyboard;

		return <div className='pane-quantum'>
			<strong>除非你知道你在做什么,不要更改此文件</strong>
			<br/>
			编辑自定义程序
			<div style={{ height: '0.5rem' }}/>
			<button
				className='light'
				onClick={ () => { keyboard.quantum = C.QUANTUM_DEFAULT; state.update(); } }>
				重置
			</button>
			<div style={{ height: '0.5rem' }}/>
			<div className='pane-quantum-editor'>
				<CodeMirror
					value={ keyboard.quantum }
					onChange={ v => { keyboard.quantum = v; state.update(); } }
					options={{
						mode: 'text/x-c',
						lineNumbers: true,
						indentUnit: 4,
						indentWithTabs: true
					}}/>
			</div>
		</div>;
	}

}

module.exports = Quantum;
